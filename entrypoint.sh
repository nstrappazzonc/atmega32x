#!/bin/sh

echo ${1}
cd /workdir/${1}/
ls -lah
make build

exit 0
