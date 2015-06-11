Star English and Long English Generator for Qt
=================

This tool takes a Qt translation file (*.ts) and generates a new one inserting either asterisks or a number of W's around each string for use to test your code for translation support.

It is for use with the [Star-English] or [Long-English] technique.

Sources
-------

If you're wanting to make changes, please clone the git repository at [sources]

git://github.com/bvanderlaan/StarEnglishGeneratorForQt.git

Documentation
-------------

### The Python Version
#### Star-English

This script takes a TS file and generates the Star-English translation strings.

You need to provide the TS file name to update.<br>
Example:<br>
```
    python createStarEnglishFile.py myApp_fo.ts
```
	
It will update myApp_fo.ts to use Star-English strings and will save the originally passed in file as myApp_fo.ts.org.

#### Long-English

This script takes a TS file and generates the Long-English translation strings.

You need to provide the TS file name to update.<br>
Example:<br>
```
    python createLongEnglishFile.py myApp_fo.ts
```
	
It will update myApp_fo.ts to use Long-English strings and will save the originally passed in file as myApp_fo.ts.org.

### The C++/Qt Version

This tool presents you with an interface which allows to you pick the source translation file and the name/location for the generated [Star-English] output file.
The source file will remain unchanged unless you tell the tool to output to the same file when picking the output name/location.


[website]: http://bradvanderlaan.ca
[Star-English]: http://imaginativethinking.ca/heck-star-english
[Long-English]: http://imaginativethinking.ca/what-the-heck-is-long-english
[sources]: https://github.com/bvanderlaan/StarEnglishGeneratorForQt

