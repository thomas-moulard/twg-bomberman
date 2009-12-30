#! /bin/sh
# $Id$

# No failure shall remain unpunished.
set -e


usage="Usage: $program [OPTION]... DIR
\$Id$

This program detects source files which contains calls to GetText.

General options:
  -D, --debug         turn on shell debugging (set -x)
  -h, --help          display this help and exit successfully
  -q, --quiet         no output unless errors (implies --batch)
  -v, --version       display version information and exit successfully
  -V, --verbose       report on what is done

  -g, --generate      generate POTFILES.in

DIR must be the directory where sources are located. If DIR is not
present, the default value ``src'' will be used.
"
version="get-translatable-files 0.1"

# We have to initialize IFS to space tab newline since we save and
# restore IFS and apparently POSIX allows stupid/broken behavior with
# empty-but-set IFS.
# http://lists.gnu.org/archive/html/automake-patches/2006-05/msg00008.html
# We need space, tab and new line, in precisely that order.  And don't
# leave trailing blanks.
newline='
'
IFS=" 	$newline"

# Pacify verbose cds.
CDPATH=${ZSH_VERSION+.}$path_sep

# In case someone crazy insists on using grep -E.
: ${EGREP=egrep}


# Default values
DIR=src

ignoredfiles='.svn Makefile'

# Initialize variables for option overriding and otherwise.
# Don't use `unset' since old bourne shells don't have this command.
# Instead, assign them an empty value.
gen=false
debug=false
quiet=false     # by default let the tools' message be displayed
verb=false      # true for verbose mode
havearg=false   # we have at least one path or file arg

## --------------------- ##
## Auxiliary functions.  ##
## --------------------- ##


# In case `local' is not supported by the shell.
(
  foo=bar
  test_local () {
    local foo=foo
  }
  test_local
  test $foo = bar
) || local () {
  case $1 in
    *=*) eval "$1";;
  esac
}


# report LINE1 LINE2...
# ---------------------
# Report some information on stderr.
report ()
{
  for i in "$@"
  do
    echo >&2 "$0: $i"
  done
}

# verbose WORD1 WORD2
# -------------------
# Report some verbose information.
verbose ()
{
  if $verb; then
    echo >&2 "$0: $@"
  fi
}

# run COMMAND-LINE
# ----------------
# Run the COMMAND-LINE verbosely, and catching errors as failures.
run ()
{
  verbose "Running $@"
  "$@" 2>&5 1>&2 ||
     error 1 "$1 failed"
}


# error EXIT_STATUS LINE1 LINE2...
# --------------------------------
# Report an error and exit with failure if EXIT_STATUS is non null.
error ()
{
  local s=$1
  shift
  report "$@"
  if test "$s" != 0; then
    exit $s
  fi
}


## ---------------------- ##
## Command line parsing.  ##
## ---------------------- ##

get_options ()
{
  # Push a token among the arguments that will be used to notice when we
  # ended options/arguments parsing.
  # Use "set dummy ...; shift" rather than 'set - ..." because on
  # Solaris set - turns off set -x (but keeps set -e).
  # Use ${1+"$@"} rather than "$@" because Digital Unix and Ultrix 4.3
  # still expand "$@" to a single argument (the empty string) rather
  # than nothing at all.
  arg_sep="$$--$$"
  set dummy ${1+"$@"} "$arg_sep"; shift

  # Parse command line arguments.
  while test x"$1" != x"$arg_sep"
  do
    # Handle --option=value by splitting apart and putting back on argv.
    case "$1" in
      --*=*)
	opt=`echo "$1" | sed -e 's/=.*//'`
	val=`echo "$1" | sed -e 's/[^=]*=//'`
	shift
	set dummy "$opt" "$val" ${1+"$@"}; shift
	;;
    esac

    # This recognizes --quark as --quiet.  So what.
    case "$1" in
      -D | --debug  ) debug=true;;
      -V | --verbose) verb=true;;
      -h | --help   ) echo "$usage"; exit 0;;
      -q | --quiet  ) quiet=true;;
      -v | --version) echo "$version"; exit 0;;

      -g | --generate) gen=true;;

      --) # What remains are not options.
	shift
	while test x"$1" != x"$arg_sep"
	do
  	    set dummy ${1+"$@"} "$1"; shift
  	    shift
	done
	break
	;;
      -*)
	error 1 "Unknown or ambiguous option \`$1'." \
  	      "Try \`--help' for more information."
	;;
      *) set dummy ${1+"$@"} "$1"; shift;;
     esac
     shift
  done
  # Pop the token
  shift

  # Interpret remaining command line args as filenames.
  case $# in
   0)
    set .
    ;;
   1) DIR=$1;;
   *)
    error 2 "Please give only one revision id."
    ;;
  esac
}

get_options "$@"

# File descriptor usage:
# 0 standard input
# 1 standard output (--verbose messages)
# 2 standard error
# 3 some systems may open it to /dev/tty
# 4 used on the Kubota Titan
# 5 tools output (turned off by --quiet)
# 6 tracing/debugging (set -x output, etc.)


# Main tools' output (TeX, etc.) that TeX users are used to seeing.
#
# If quiet, discard, else redirect to the message flow.
if $quiet; then
  exec 5>/dev/null
else
  exec 5>&1
fi
# Enable tracing, and auxiliary tools output.
#
# Should be used where you'd typically use /dev/null to throw output
# away.  But sometimes it is convenient to see that output (e.g., from
# a grep) to aid debugging.  Especially debugging at distance, via the
# user.
if $debug; then
  exec 6>&1
  set -x
else
  exec 6>/dev/null
fi

verbose "Search for translatable source files in ''$DIR''."

res=$(grep -R 'gettext' $DIR)

verbose "Remove ignored files/directories."

for d in $ignoredfiles; do
    verbose "+ $d"
    res=$(echo "$res" | grep -v "$d")
done

verbose "Extract filenames."
res=$(echo "$res" | cut -d':' -f1 | uniq | sort)

if test "$gen" = "false"; then
 verbose "Print results."
 for f in $res; do
  echo $f
 done
else
 verbose "Generate POTFILES.in."

 echo "# List of source files which contain translatable strings." \
  > POTFILES.in

 date=$(date -R)
 echo "# Generated: $date" >> POTFILES.in
 echo "" >> POTFILES.in
 for f in $res; do
  echo $f >> POTFILES.in
 done
fi