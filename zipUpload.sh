#!/bin/sh

NOW=`date +%FT%H-%M-%S`
zip -r upload-$1_${NOW}.zip src
chown 911.911 upload-$1_${NOW}.zip
