Star English Generator for Qt
=================

This tool takes a Qt translation file (*.ts) and generates a new one inserting asterisks around each string for use to test your code for translation support.

It is for use with the [Star-English] technique.

Sources
-------

If you're wanting to make changes, please clone the git repository at [sources]

git://github.com/bvanderlaan/StarEnglishGeneratorForQt.git

Documentation
-------------

This script takes a TS file and generates the star english translation strings.

You need to provide the TS file name to update.<br>
Example:<br>
```
    python createStarEnglishFile.py myApp_fo.ts
```
	
It will update myApp_fo.ts to use Star English strings and will save the orignally passed in file as myApp_fo.ts.org.


[website]: http://bradvanderlaan.ca
[Star-English]: http://imaginativethinking.ca/what-the-heck-is-star-english
[sources]: https://github.com/bvanderlaan/StarEnglishGeneratorForQt
