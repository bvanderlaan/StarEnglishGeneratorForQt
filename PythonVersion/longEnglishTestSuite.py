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

import ca.imaginativethinking.translation_generator as tg
import xml.etree.ElementTree as etree
import unittest


class LongEnglishGeneratorTester(tg.LongEnglishGenerator):
    def __init__(self):
        tg.LongEnglishGenerator.__init__(self, "")

    def _parse_xml_data(self, translation_file):
        root = etree.fromstring(translation_file)
        translation_xml_tree = etree.ElementTree(root)
        return translation_xml_tree


class TestGeneratingLongEnglish(unittest.TestCase):

    def test_generating_long_english_when_entry_is_already_translated(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>HELLO WORLD</source><translation>Bonjour Le Monde</translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>HELLO WORLD</source><translation>Bonjour Le Monde</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_when_translation_attribute_not_unfinished(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>HELLO WORLD</source><translation type=\"finished\" someOtherAttribute=\"true\">Hello World</translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>HELLO WORLD</source><translation someOtherAttribute=\"true\" type=\"finished\">Hello World</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_when_no_translation_exists(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>HELLO WORLD</source><translation type=\"unfinished\" /></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>HELLO WORLD</source><translation>WWWWWHELLO WORLDWWWWW</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_when_no_translation_exists_but_some_other_attribute_does(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>HELLO WORLD</source><translation type=\"unfinished\" someOtherAttribute=\"true\"></translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>HELLO WORLD</source><translation someOtherAttribute=\"true\">WWWWWHELLO WORLDWWWWW</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_with_multiple_contexts_and_multiple_messages(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>HELLO WORLD</source><translation type=\"unfinished\" /></message><message><source>FU BAR</source><translation type=\"unfinished\" /></message></context>"
                                                                   + "<context><message><source>Test Message</source><translation type=\"unfinished\" /></message><message><source>One Two Three</source><translation type=\"unfinished\" /></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>HELLO WORLD</source><translation>WWWWWHELLO WORLDWWWWW</translation></message><message><source>FU BAR</source><translation>WWWFU BARWWW</translation></message></context><context><message><source>Test Message</source><translation>WWWWWWTest MessageWWWWWW</translation></message><message><source>One Two Three</source><translation>WWWWWWOne Two ThreeWWWWWW</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_with_miss_ordered_tags(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><translation type=\"unfinished\"></translation><source>Hello World</source></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><translation>WWWWWHello WorldWWWWW</translation><source>Hello World</source></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_with_location_tag_used_by_qml(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><location filename=\"myapp/qml/myapp/screens/MyScreen.qml\" line=\"501\"/><source>Hello World</source><translation type=\"unfinished\"></translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><location filename=\"myapp/qml/myapp/screens/MyScreen.qml\" line=\"501\" /><source>Hello World</source><translation>WWWWWHello WorldWWWWW</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_with_multiple_location_tag_used_by_qml(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><location filename=\"myapp/qml/myapp/screens/MyScreen.qml\" line=\"501\"/><location filename=\"myapp/qml/myapp/screens/MyScreen.qml\" line=\"605\"/><source>Hello World</source><translation type=\"unfinished\"></translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><location filename=\"myapp/qml/myapp/screens/MyScreen.qml\" line=\"501\" /><location filename=\"myapp/qml/myapp/screens/MyScreen.qml\" line=\"605\" /><source>Hello World</source><translation>WWWWWHello WorldWWWWW</translation></message></context></TS>"
        self.assertEqual(actual, expected)

    def test_generating_long_english_with_context_comments(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>Hello World</source><comment>This is just showing how a context comment looks in the TS file.</comment><translation type=\"unfinished\"></translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>Hello World</source><comment>This is just showing how a context comment looks in the TS file.</comment><translation>WWWWWHello WorldWWWWW</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_with_extra_comments(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message><source>Hello World</source><extracomment>This is an example of an extra comment</extracomment><translation type=\"unfinished\"></translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message><source>Hello World</source><extracomment>This is an example of an extra comment</extracomment><translation>WWWWWHello WorldWWWWW</translation></message></context></TS>"
        self.assertEqual(expected, actual)

    def test_generating_long_english_with_numerus_forms(self):
        generator_tester = LongEnglishGeneratorTester()
        actual_tree = generator_tester._generate_modified_xml_tree("<TS><context><message numerus=\"yes\"><source>Month(s)</source><translation type=\"unfinished\"><numerusform></numerusform><numerusform></numerusform></translation></message></context></TS>")
        actual = etree.tostring(actual_tree.getroot(), encoding="unicode")
        expected = "<TS><context><message numerus=\"yes\"><source>Month(s)</source><translation><numerusform>WWWWMonthWWWW</numerusform><numerusform>WWWWMonthsWWWW</numerusform></translation></message></context></TS>"
        self.assertEqual(expected, actual)

if __name__ == "__main__":
    unittest.main()
