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
import xml.etree.ElementTree as etree


def print_help_message():
    print("===============================================")
    print("  Create Star English Translation File for Qt")
    print("                                  Version 1.0.0")
    print("===============================================")
    print("This script takes a TS file and generates the star english translation strings.")
    print("")
    print("You need to provide the TS file name to update.")
    print("Example:")
    print("    python createStarEnglishFile.py myApp_fo.ts")


def open_translation_file(source_translation_file, open_mode):
    try:
        xml_file = open(source_translation_file, open_mode)
    except FileNotFoundError:
        xml_file = 0
        print("Error: Could not open the Translation file.")
    return xml_file


def process_message_entry(message_element):
    if message_element.tag == "message":
        translation_element = message_element.find("translation")
        if translation_element.get("type") == "unfinished":
            original_string = message_element.find("source").text
            translation_element.text = "*"+original_string+"*"
            translation_element.attrib.pop("type")


def process_context_entry(context_element):
    if context_element.tag == "context":
        for element in context_element:
            process_message_entry(element)


def generate_star_english_xml_tree(translation_file):
    translation_xml_tree = etree.parse(translation_file)

    for element in translation_xml_tree.getroot():
        process_context_entry(element)

    return translation_xml_tree


def save_original_file(original_translation_filename):
    backup_filename = original_translation_filename + ".org"
    original_xml_tree = etree.parse(original_translation_filename)
    original_xml_tree.write(backup_filename)
    print("Backed up the original file here: ", backup_filename)

def generate_star_english_file(source_translation_filename):
    translation_file = open_translation_file(source_translation_filename, "rb")

    if translation_file:
        save_original_file(source_translation_filename)
        star_english_xml_tree = generate_star_english_xml_tree(translation_file)
        translation_file.close()
        star_english_xml_tree.write(source_translation_filename)
        print("Done.")
        print(source_translation_filename, " has been updated to be Star English.")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        print("================================")
        print("Generating Star English Translation file for: ", sys.argv[1])
        generate_star_english_file(sys.argv[1])
        print("================================")
    else:
        print_help_message()