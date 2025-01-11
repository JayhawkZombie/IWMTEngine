import argparse
from datetime import datetime
import common
import reflection

start_time = datetime.now()

if __name__ == '__main__':
    start_time = datetime.now()
    parser = argparse.ArgumentParser(
        description='Generate reflection files from input directory'
    )
    parser.add_argument(
        '--input', required=True,
        help='Directory with input files'
    )
    parser.add_argument(
        '--output', required=True,
        help='Directory with output files'
    )
    parser.add_argument(
        '-v', '--verbose',
        default=False,
        action='store_true',
        help='Verbose output'
    )
    args = parser.parse_args()
    common.debug_log("Generating reflection data")
    reflection.generate_reflection_data(args.input, args.output, args.verbose or False)
