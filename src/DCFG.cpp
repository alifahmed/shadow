#include "DCFG.h"
#include "InsBlock.h"

using namespace std;

DCFG::DCFG(InsBlock *&beginBlock, InsBlock *&endBlock, const std::string &dcfg_cfg_file) {
    shadow_output.open("shadow_output.out", ofstream::out);
    dcfg_output.open("dcfg_output.out", ofstream::out);

    dcfgMgr = DCFG_PIN_MANAGER::new_manager();
	dcfgMgr->set_cfg_collection(true);
	dcfgMgr->activate();

    dcfgData = DCFG_DATA::new_dcfg();
	string msg;
	if (dcfgData->read(dcfg_cfg_file, msg)) {
		DCFG_ID_VECTOR process_ids;
		int process_count = dcfgData->get_process_ids(process_ids);
		assert(process_count >= 1);

		dcfgProcInfo = dcfgData->get_process_info(process_ids[0]);

		initDCFGMap(beginBlock, endBlock);
	}
    else {
        cerr << "DCFG cfg file not existent, creating one using current run." << endl;
    }
}

void DCFG::initDCFGMap(InsBlock *&beginBlock, InsBlock *&endBlock) {
	beginBlock = new InsBlock();
	endBlock = new InsBlock();
	this->beginBlock = beginBlock;
	this->endBlock = endBlock;

	DCFG_ID_VECTOR bblids, edge_ids, temp_ids;
	dcfgProcInfo->get_basic_block_ids(bblids);

    // create a special "UNKNOWN" node whose BBLID is 3 in DCFG
	DCFGMap[3] = new InsBlock();

	for (DCFG_ID id: bblids) {
		DCFGMap[id] = new InsBlock();
		DCFGMap[id]->dcfgid = id;
	}

	dcfgProcInfo->get_internal_edge_ids(edge_ids);
	temp_ids.clear();
	dcfgProcInfo->get_inbound_edge_ids(temp_ids);
	edge_ids.insert(edge_ids.end(), temp_ids.begin(), temp_ids.end());
	temp_ids.clear();
	dcfgProcInfo->get_outbound_edge_ids(temp_ids);
	edge_ids.insert(edge_ids.end(), temp_ids.begin(), temp_ids.end());

	DCFG_ID begin_id = dcfgProcInfo->get_start_node_id();
	DCFG_ID end_id = dcfgProcInfo->get_end_node_id();

	for (DCFG_ID id: edge_ids) {
		DCFG_EDGE_CPTR e = dcfgProcInfo->get_edge_info(id);
		DCFG_ID src = e->get_source_node_id();
		DCFG_ID dst = e->get_target_node_id();

		UINT64 cnt = e->get_exec_count();
		// std::cout << src << " " << dst << " " << cnt << std::endl;
		InsBlock *src_block = (src == begin_id ? beginBlock : DCFGMap[src]);
		InsBlock *dst_block = (dst == end_id ? endBlock : DCFGMap[dst]);
		src_block->outEdges.insert(dst_block);
		src_block->outEdgesStack.push_back({dst_block, cnt});
		dst_block->inEdges.insert(src_block);
	}
}

void DCFG::recordBBL(DCFG *self, InsBlock *cur) {
	// InsBlock *prev = self->prevBlockinTrace;
	// cout << "cur = " << (void *) cur << endl;
	// TODO: record all traces for now
	if (self->prevBlockinTrace != nullptr) {
		// cout << (void *) prev << endl;
		if (self->prevBlockinTrace->outEdgesTrace.empty()) {
			//no out edge yet. add.
			self->prevBlockinTrace->outEdgesTrace.push_back( { cur, 1 });
		} else if (self->prevBlockinTrace->outEdgesTrace.back().first == cur) {
			//same as last one. increment count.
			self->prevBlockinTrace->outEdgesTrace.back().second++;
		} else {
			//not same as last one. add.
			self->prevBlockinTrace->outEdgesTrace.push_back( { cur, 1 });
		}
	}
	self->prevBlockinTrace = cur;
}

InsBlock *DCFG::getInsBlockByBBLAddress(ADDRINT addr) {
    DCFG_ID_VECTOR bblids;
    if (!this->exist()) return nullptr;
    dcfgProcInfo->get_basic_block_ids_by_addr(addr, bblids);
    UINT64 bblid = BBL_INVALID;
    if (bblids.size() <= 0) return nullptr;
    bblid = bblids[0];
    auto it = DCFGMap.find(bblid);

    if (it == DCFGMap.end()) return nullptr;
    return it->second;
}

void DCFG::write(const std::string &file) {
    DCFG_DATA_CPTR data = dcfgMgr->get_dcfg_data();
	string msg;
	data->write(file, msg);
}

// void DCFG::compressDCFG(std::set<InsBlock *> &cfg) {
// 	for (InsBlock *blk : cfg) {
// 		if (blk != this->beginBlock && blk != this->endBlock) {
// 			// if there are no instructions in this block
// 			// and this block is sequential
// 			if (blk->ins.size() == 0 && blk->inEdges.size() == 1 && blk->outEdges.size() == 1) {
				
// 				InsBlock *prev = *blk->inEdges.begin();
// 				InsBlock *next = *blk->outEdges.begin();
// 				// std::cout << prev->getId() << " " << blk->getId() << " " << next->getId() << std::endl;
// 				prev->replaceOutEdge(blk, next);
// 				next->inEdges.erase(blk);
// 				next->inEdges.insert(prev);
// 				blk->isUsed = false;
// 				cfg.erase(blk);
// 			}
// 		}
// 	}
// }

// bool reloadDcfgTraceBuffer() {
// 	string msg;
// 	dcfgTraceBuffer.clear();
// 	if (!dcfg_trace_done) {
// 		if (!dcfgTraceReader->get_edge_ids(dcfgTraceBuffer, dcfg_trace_done, msg)) {
// 			cerr << " error: " << msg << endl;
// 			dcfg_trace_done = true;
// 			return false;
// 		}
// 		dcfgTraceBufferPtr = dcfgTraceBuffer.begin();
// 		return true;
// 	}
// 	return false;
// }

// UINT64 getDcfgEdgeAddress(DCFG_ID_VECTOR::iterator &edgePtr) {
// 	DCFG_EDGE_CPTR edge = dcfgProcInfo->get_edge_info(*edgePtr);
// 	if (!edge) {
// 		cerr << "error: invalid edge" << endl;
// 		return 0; 
// 	}
// 	DCFG_ID bbId = edge->get_target_node_id();
// 	DCFG_BASIC_BLOCK_CPTR bb = dcfgProcInfo->get_basic_block_info(bbId);
	
// 	if (!bb) return 0;
// 	// if (edge->is_exit_edge_type()) {
// 	// 	dcfg_output << bbId << " " << (void *)bb->get_first_instr_addr() << ",end" << endl;
// 	// 	return 0;
// 	// }
// 	return bb->get_first_instr_addr();
// }