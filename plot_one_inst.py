#!/usr/bin/env python3

import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) != 3:
	print("Usage: ./plot_one_inst.py <trace_file> <inst_id>")
	sys.exit(-1)

trace_file = sys.argv[1]
inst_id = sys.argv[2]

df = pd.read_csv(trace_file)
print(df.head())
df_mask = df["ins"] == int(inst_id)
print(df_mask.head())
df_sel = df[df_mask]
print(df_sel.head())

sz = df_sel.shape[0]
#min_addr = min(df_sel['addr'])

plt.figure()
plt.scatter(range(sz), df_sel['addr'])
plt.show()

