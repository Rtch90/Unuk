#!/bin/bash

echo "cpp - `find . -name '*.cpp' -print0 | wc -l --files0-from=- | tail -n1`"
echo "h - `find . -name '*.h' -print0 | wc -l --files0-from=- | tail -n1`"
