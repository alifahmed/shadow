#!/usr/bin/env python3

# BEGIN_LEGAL
# BSD License
#
# Copyright (c)2015 Intel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.  Redistributions
# in binary form must reproduce the above copyright notice, this list of
# conditions and the following disclaimer in the documentation and/or
# other materials provided with the distribution.  Neither the name of
# the Intel Corporation nor the names of its contributors may be used to
# endorse or promote products derived from this software without
# specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
# ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# END_LEGAL
#
#
# @ORIGINAL_AUTHORS: T. Mack Stallcup, Cristiano Pereira, Harish Patil, Chuck Yount
#
#
# $Id: rename.py,v 1.22 2015/08/15 20:02:00 tmstall Exp tmstall $

import sys
import os
import datetime
import glob
import optparse

import cmd_options
import config
import msg
import util
"""
@package rename

Rename the original PinPoint trace files to conform to the Intel trace
library naming requirements.  Creates a symblic link instead of copying the
file.  This saves space and retains an explicit documentation of the name
changes.
"""

# Objects
#
Config = config.ConfigClass()

############################################################################


def CheckField(string):
    """
    Check to make sure a string doesn't contain any characters the GTR does not allow.

    Char '.' and '_' are not allowed as field names for files in the GTR.
    """

    err_msg = lambda string, char: msg.PrintAndExit("String '%s' contains the illegal "\
                "character '%s'.\n" \
                "Characters '.' and '_' are NOT allowed in GTR file names." % (string, char))

    char = '.'
    if string.find(char) != -1:
        err_msg(string, char)
    char = '_'
    if string.find(char) != -1:
        err_msg(string, char)


def CheckRequiredVariables(options):
    """Check to make sure all the required input variables are defined."""

    if options.app_version == '':
        msg.PrintAndExit("Required parameter \'app_version\' not found.\n"
                         "This must be defined in order to run the script.")
    if options.compiler_version == '':
        msg.PrintAndExit("Required parameter \'compiler_version\' not found.\n"
                         "This must be defined in order to run the script.")
    if options.input_name == '':
        msg.PrintAndExit("Required parameter \'input_name\' not found.\n"
                         "This must be defined in order to run the script.")
    if options.program_name == '':
        msg.PrintAndExit("Required parameter \'program_name\' not found.\n"
                         "This must be defined in order to run the script.")
    if options.platform == '':
        msg.PrintAndExit("Required parameter \'platform\' not found.\n"
                         "This must be defined in order to run the script.")

    # Check for any illegal char in these fields.
    #
    CheckField(options.app_version)
    CheckField(options.compiler_version)
    CheckField(options.input_name)
    CheckField(options.program_name)
    CheckField(options.platform)


def GetOptions():
    """Get users command line options."""

    version = '$Revision: 1.22 $'
    version = version.replace(' ', '')
    ver = version.replace(' $', '')
    us = '%prog [options] app_version compiler_version input_name platform program_name'
    desc = \
    'Renames tracing files generated by PinPlay tools to conform to the GTR requirements.  ' \
    'There are 5 arguments required to run the script.  Details are given below in the ' \
    'section \'Required arguments\'.'

    # Print arguments passed to the script.
    #
    # import pdb;  pdb.set_trace()
    msg.PrintMsgNoCR('Script args: '),
    for string in sys.argv[1:]:
        msg.PrintMsgNoCR(string + ' '),
    msg.PrintMsg('')
    msg.PrintMsg('')

    util.CheckNonPrintChar(sys.argv)
    parser = optparse.OptionParser(
        usage=us,
        version=ver,
        description=desc,
        formatter=cmd_options.BlankLinesIndentedHelpFormatter())

    # Command line options to control the scripts behavior.
    #
    # import pdb;  pdb.set_trace()
    cmd_options.config_file(parser)
    cmd_options.debug(parser)
    cmd_options.date(parser, '')
    cmd_options.processor(parser, '')
    cmd_options.verbose(parser)

    # Define a separate option group for the require arguments.
    #
    required_opts = cmd_options.RenameRequiredOpts(parser)

    cmd_options.app_version(parser, required_opts)
    cmd_options.compiler_version(parser, required_opts)
    cmd_options.input_name(parser, required_opts)
    cmd_options.platform(parser, required_opts)
    cmd_options.program_name(parser, required_opts)

    parser.add_option_group(required_opts)

    (options, args) = parser.parse_args()

    # Added method cbsp() to 'options' to check if running CBSP.
    #
    util.AddMethodcbsp(options)

    # Read in the configuration file.
    #
    Config.GetCfgGlobals(options, True)  # 2 required parameters are needed

    # Ensure the required variables are defined.
    #
    CheckRequiredVariables(options)

    # If the user didn't give a date, use the current date.
    #
    if options.date == '':
        today = datetime.date.today()
        options.date = today.strftime('%y%m')
    CheckField(options.date)

    # If user didn't give a separate processor name, get it from the platform info.
    #
    if options.processor == '':
        # Use the first 3 char as the processor type
        options.processor = options.platform[:3]
    CheckField(options.processor)

    return options

############################################################################

# Host is always 'pin'.  
# OS is Linux64.  May need to change this to be an option for Windows.
#
host = 'pin'
operating_sys = 'linux64'

options = GetOptions()

# Define a lambda function to print an error message.
#
err_msg = lambda string: msg.PrintMsg(
    'ERROR: util.ParseFileName() failed to get field: ' + string)

# import pdb;  pdb.set_trace()

# For each LIT directory, create a link to each file which is formatted properly
# to be submitted to the GTR.
#
dirs = util.GetLitDir()
dirs.sort()
for lit_dir in dirs:

    # Make sure the LIT directory exists, then go there.
    #
    # import pdb;  pdb.set_trace()
    old_dir = os.getcwd()
    if os.path.isdir(lit_dir):
        os.chdir(lit_dir)
        msg.PrintMsg('Dir: ' + os.path.basename(os.getcwd()))
    else:
        msg.PrintAndExit('ERROR: The LIT directory does not exist:\n   ' + \
                         lit_dir)

    # Get a list of the simulator files for each trace. Don't include any of the
    # PinPlay files.
    #
    files = ['*lit*']
    files += ['*arch*']
    files += ['*ami*']
    files += ['*cmd*']
    files += ['*cpuid*']
    files += ['*procinfo*']
    files += ['*tzcat*']
    lit_files = []
    for f in files:
        lit_files += glob.glob(f)

    for old_name in lit_files:

        # Parse the file name to get some fields used for the new name
        #
        # import pdb;  pdb.set_trace()
        field = util.ParseFileName(old_name)

        # PID is an optional field
        #
        try:
            pid = field['pid']
        except:
            pid = ''

        # Verify the required fields were in the file name.
        #
        try:
            tid = field['tid']
        except:
            err_msg('tid')
            sys.exit(-1)
        try:
            trace_num = field['trace_num']
        except:
            err_msg('trace_num')
            sys.exit(-1)
        try:
            file_ext = field['file_ext']
        except:
            err_msg('file_ext')
            sys.exit(-1)

        # Remove TID from the file extension, if it exists.
        #
        # import pdb;  pdb.set_trace()
        tmp = file_ext.split('.')
        if tmp[1].isdigit():
            file_ext = tmp[2:]
            file_ext = '.'.join(file_ext)

        # Format some additional data used as fields in the GTR file name.
        #
        if pid:
            remark = 'pid-' + str(pid) + '-tid-' + str(tid)
        else:
            # Only use the TID.
            #
            remark = 'tid-' + str(tid)

        # Check for any illegal char in fields.
        #
        CheckField(host)
        CheckField(operating_sys)
        CheckField(remark)

        # Generate the GTR approved file name.
        #
        new_name = host + '_'
        new_name += options.program_name + '_'
        new_name += options.input_name + '_'
        new_name += options.app_version + '_'
        new_name += operating_sys + '_'
        new_name += options.compiler_version + '_'
        new_name += options.platform + '_'
        new_name += remark + '_'
        new_name += options.date + '_'
        new_name += '%03d' % trace_num + '.'
        new_name += options.processor + '.'
        new_name += file_ext

        # Just make a symbolic link to the new name.  This saves
        # lots of file space.
        #
        msg.PrintMsg('Old name: ' + old_name)
        msg.PrintMsg('New name: ' + new_name)
        # import pdb;  pdb.set_trace()
        if not options.debug:
            os.symlink(old_name, new_name)
            msg.PrintMsg('')
        else:
            msg.PrintMsg('Cmd: ln -s %s %s\n' % (old_name, new_name))

    # Return to the working directory.
    #
    os.chdir(old_dir)

# For each LIT directory, create a link to it for the remainder
# of the scripts to use. 
#
proc = 1
for lit_dir in dirs:
    new_dir = 'proc-' + str(proc)
    msg.PrintMsg('Old dir: ' + lit_dir)
    msg.PrintMsg('New dir: ' + new_dir)
    # import pdb;  pdb.set_trace()
    if not options.debug:
        if not os.path.exists(new_dir):
            os.symlink(lit_dir, new_dir)
        else:
            msg.PrintMsg('NOTE: dir already exists.  It will not be created.')
            msg.PrintMsg('   ' + new_dir)
    else:
        msg.PrintMsg('Cmd: ln -s %s %s\n' % (lit_dir, new_dir))
    proc += 1

sys.exit(0)
