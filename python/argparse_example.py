#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import argparse

g_optarg = None

def get_arg_parser():
    example_text = '''examples:
    {cmd} --help
    {cmd} --version
    {cmd} -v
    '''.format(cmd=sys.argv[0])

    parser = argparse.ArgumentParser(add_help=False,
                                     epilog=example_text,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('-h', '--help', action='help',
                        help='show this help message and exit')
    parser.add_argument('--version', action='version', version='%(prog)s 1.0')
    parser.add_argument('-v', '--verbose',
                        dest='verbose',
                        action='store_true',
                        default=False,
                        help='verbose information')

    parser.add_argument('--test',
                        dest='test',
                        action='store_true',
                        default=False,
                        help='test')
    parser.add_argument('--start',
                        dest='start',
                        action='store',
                        default=0,
                        help='start time, default 0')

    # 最后的参数列表
    parser.add_argument('args', action='store', nargs='*', help='files')

    return parser

def main(argv):
    global g_optarg
    parser = get_arg_parser()
    g_optarg = parser.parse_args(argv[1:])
    print(g_optarg)
    if g_optarg.test:
        parser.print_help()
        return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv))
