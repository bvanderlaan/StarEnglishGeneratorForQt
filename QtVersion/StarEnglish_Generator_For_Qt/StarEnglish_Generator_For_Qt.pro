TEMPLATE = subdirs
SUBDIRS += starenglishgeneratorapp \
          starenglishgeneratorlib \
          seGenUnitTests

seGenUnitTests.depends = starenglishgeneratorlib
starenglishgeneratorapp.depends = starenglishgeneratorlib
