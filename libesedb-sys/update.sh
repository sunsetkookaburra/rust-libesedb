#!/usr/bin/env sh

LOCAL_LIBS="libesedb libbfio libcdata libcerror libcfile libclocale libcnotify libcpath libcsplit libcthreads libfcache libfdata libfdatetime libfguid libfmapi libfvalue libfwnt libmapidb libuna";

for LOCAL_LIB in ${LOCAL_LIBS}; do
  echo "Updating ${LOCAL_LIB}"
  (cd $(dirname $0); cd ${LOCAL_LIB}; git fetch; git checkout $(git tag -l --sort=-taggerdate | tail -1))
done
