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


class StarEnglishGenerator():
    def __init__(self, source_translation_file):
        self.__source_translation_file = source_translation_file
        self.__star_english_marker = '*'

    def __open_translation_file(self, open_mode):
        try:
            xml_file = open(self.__source_translation_file, open_mode)
        except FileNotFoundError:
            xml_file = 0
            print("Error: Could not open the Translation file.")
        return xml_file

    def __insert_star_english_string(self, translation_element, original_string, is_numerus):
        if is_numerus:
            numerusform_elements = translation_element.findall("numerusform")
            numerusform_elements[0].text = self.__star_english_marker + original_string[:-3] + self.__star_english_marker
            numerusform_elements[1].text = self.__star_english_marker + original_string.replace("(","").replace(")","") + self.__star_english_marker
        else:
            translation_element.text = self.__star_english_marker + original_string + self.__star_english_marker

    def __process_message_entry(self, message_element):
        if message_element.tag == "message":
            is_numerus = (message_element.get("numerus") == "yes")
            translation_element = message_element.find("translation")
            if translation_element.get("type") == "unfinished":
                original_string = message_element.find("source").text
                self.__insert_star_english_string(translation_element, original_string, is_numerus)
                translation_element.attrib.pop("type")

    def __process_context_entry(self, context_element):
        if context_element.tag == "context":
            for element in context_element:
                self.__process_message_entry(element)

    def _parse_xml_data(self, translation_file):
        translation_xml_tree = etree.parse(translation_file)
        return translation_xml_tree

    def _generate_star_english_xml_tree(self, translation_file):
        translation_xml_tree = self._parse_xml_data(translation_file)

        for element in translation_xml_tree.getroot():
            self.__process_context_entry(element)

        return translation_xml_tree

    def __save_original_file(self):
        backup_filename = self.__source_translation_filename + ".org"
        original_xml_tree = etree.parse(self.__source_translation_filename)
        original_xml_tree.write(backup_filename)
        print("Backed up the original file here: ", backup_filename)

    def generate_star_english_file(self):
        translation_file = self.__open_translation_file("rb")

        if translation_file:
            self.__save_original_file()
            star_english_xml_tree = self.__generate_star_english_xml_tree(translation_file)
            translation_file.close()
            star_english_xml_tree.write(self.__source_translation_filename)
            print("Done.")
            print(self.__source_translation_filename, " has been updated to be Star English.")


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


if __name__ == "__main__":
    if len(sys.argv) > 1:
        print("================================")
        print("Generating Star English Translation file for: ", sys.argv[1])
        generator = StarEnglishGenerator(sys.argv[1])
        generator.generate_star_english_file()
        print("================================")
    else:
        print_help_message()