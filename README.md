## dtree

[![Test Build Status](https://travis-ci.org/pahoughton/dtree.png)](https://travis-ci.org/pahoughton/dtree)
```
Usage: dtree dirname [-[D|d][S|s][F|f]] [-l logfilename]

  -D         turn on debug output
  -d         turn off debug output (default)
  -S	        trun on log to screen (default)
  -s         turn off log to screen
  -F         turn on log to file
  -s         turn of log to file
  -l fn      log file name
  -i ignore  file names to ignore (CVS|RCS|SCCS)
```


## Install

See Makefile (fyi no install target)

## Usage

```
dtree
.
   |---.git
   |   |---branches
   |   |---logs
   |   |   |---refs
   |   |   |   |---heads
   |   |   |   |---remotes
   |   |   |   |   |---origin
   |   |---objects
   |   |   |---info
   |   |   |---pack
   |   |---hooks
   |   |---refs
   |   |   |---heads
   |   |   |---tags
   |   |   |---remotes
   |   |   |   |---origin
   |   |---info

```
## Contribute

[Github pahoughton/..](https://github.com/pahoughton/dtree)

## Licenses

Copyright (cc) 2014 Paul Houghton <paul4hough@gmail.com>

[![LICENSE](http://i.creativecommons.org/l/by/3.0/88x31.png)](http://creativecommons.org/licenses/by/3.0/)

[![endorse](https://api.coderwall.com/pahoughton/endorsecount.png)](https://coderwall.com/pahoughton)
