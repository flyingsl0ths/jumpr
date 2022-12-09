#!/bin/bash

if [[ "$1" == "debug" ]]; then
  cd .. &&
    ./build/db/app/jumpr "$(pwd)"
elif [[ "$1" == "prod" ]]; then
  ./build/rl/app/jumpr "$(pwd)"
fi
