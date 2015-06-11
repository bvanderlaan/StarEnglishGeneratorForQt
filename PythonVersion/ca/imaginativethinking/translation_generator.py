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

import xml.etree.ElementTree as etree


class TranslationGenerator():
    def __init__(self, source_translation_file):
        self._source_translation_filename = source_translation_file

    def generate(self):
        translation_file = self.__open_translation_file("rb")

        if translation_file:
            self.__save_original_file()
            modified_xml_tree = self._generate_modified_xml_tree(translation_file)
            translation_file.close()
            modified_xml_tree.write(self._source_translation_filename)
            print("Done.")

    def __open_translation_file(self, open_mode):
        try:
            xml_file = open(self._source_translation_filename, open_mode)
        except FileNotFoundError:
            xml_file = 0
            print("Error: Could not open the Translation file.")
        return xml_file

    def __save_original_file(self):
        backup_filename = self._source_translation_filename + ".org"
        original_xml_tree = etree.parse(self._source_translation_filename)
        original_xml_tree.write(backup_filename)
        print("Backed up the original file here: ", backup_filename)

    def _generate_modified_xml_tree(self, translation_file):
        translation_xml_tree = self._parse_xml_data(translation_file)

        for element in translation_xml_tree.getroot():
            self.__process_context_entry(element)

        return translation_xml_tree

    def _parse_xml_data(self, translation_file):
        translation_xml_tree = etree.parse(translation_file)
        return translation_xml_tree

    def __process_context_entry(self, context_element):
        if context_element.tag == "context":
            for element in context_element:
                self.__process_message_entry(element)

    def __process_message_entry(self, message_element):
        if message_element.tag == "message":
            is_numerus = (message_element.get("numerus") == "yes")
            translation_element = message_element.find("translation")
            if translation_element.get("type") == "unfinished":
                original_string = message_element.find("source").text
                self._insert_translation_string(translation_element, original_string, is_numerus)
                translation_element.attrib.pop("type")

    def _insert_translation_string(self, translation_element, original_string, is_numerus):
        pass


class StarEnglishGenerator(TranslationGenerator):
    def __init__(self, source_translation_file):
        TranslationGenerator.__init__(self, source_translation_file)
        self.__star_english_marker = '*'

    def generate(self):
        TranslationGenerator.generate(self)
        print(self._source_translation_filename, " has been updated to be Star English.")

    def _insert_translation_string(self, translation_element, original_string, is_numerus):
        if is_numerus:
            numerusform_elements = translation_element.findall("numerusform")
            numerusform_elements[0].text = self.__star_english_marker + original_string[:-3] + self.__star_english_marker
            numerusform_elements[1].text = self.__star_english_marker + original_string.replace("(", "").replace(")", "") + self.__star_english_marker
        else:
            translation_element.text = self.__star_english_marker + original_string + self.__star_english_marker


class LongEnglishGenerator(TranslationGenerator):
    def __init__(self, source_translation_file):
        TranslationGenerator.__init__(self, source_translation_file)
        self.__long_english_marker = 'W'

    def generate(self):
        TranslationGenerator.generate(self)
        print(self._source_translation_filename, " has been updated to be Long English.")

    def _insert_translation_string(self, translation_element, original_string, is_numerus):
        marker = self.__get_long_english_marker(original_string)
        if is_numerus:
            numerusform_elements = translation_element.findall("numerusform")
            numerusform_elements[0].text = marker + original_string[:-3] + marker
            numerusform_elements[1].text = marker + original_string.replace("(", "").replace(")", "") + marker
        else:
            translation_element.text = marker + original_string + marker

    def __get_long_english_marker(self, original_string):
        return self.__long_english_marker * (len(original_string)//2)
