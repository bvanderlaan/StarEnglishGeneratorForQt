# Copyright 2015 ImaginativeThinking
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import ca.imaginativethinking.translation_generator as tg


def print_help_message():
    print("===============================================")
    print("  Create Long English Translation File for Qt")
    print("                                  Version 1.0.0")
    print("===============================================")
    print("This script takes a TS file and generates the long english translation strings.")
    print("")
    print("You need to provide the TS file name to update.")
    print("Example:")
    print("    python createLongEnglishFile.py myApp_fo.ts")


if __name__ == "__main__":
    if len(sys.argv) > 1:
        print("================================")
        print("Generating Long English Translation file for: ", sys.argv[1])
        generator = tg.LongEnglishGenerator(sys.argv[1])
        generator.generate()
        print("================================")
    else:
        print_help_message()