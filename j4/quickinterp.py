#!/bin/python3
def usage():
    print(
"""=== J4 python interpreter==
usage: quickinterp.py <input_file> 
    """)

import importlib.machinery
import importlib.util
import sys
import os

# J4 importability check
if not "J4_PATH" in os.environ:
    print("Error: J4_PATH environment variable is not set. Please set it.")
    sys.exit(-1)
else:
    sys.path.append(os.environ["J4_PATH"] + "/..")
from j4.interp.interp import big_interp, Env
from j4.core.desugar import desugar


def main():
    if len(sys.argv) != 2:
        usage()
        return

    parsable = True

    try:
        input_loader = importlib.machinery.SourceFileLoader("j4_exe", sys.argv[1])
        input_spec = importlib.util.spec_from_loader(input_loader.name, input_loader)
        input_module = importlib.util.module_from_spec(input_spec)
        input_loader.exec_module(input_module)
        try:
            # input_module.main.pp()
            program = desugar(input_module.main)
        except AttributeError:
            print("        printf(\"Error: input file does contain main attribute.\\n\") ;")
            parsable = False
    except FileNotFoundError:
        print("        printf(\"Error: input file does not exist.\\n\") ;")
        parsable = False
    if parsable:
        program.pp()
        # program.exprs[0].pp()
        # program.exprs[1].pp()
        # print("BEGIN")
        result = big_interp(program, Env())
        print(result.value)

if __name__ == "__main__":
    main()
