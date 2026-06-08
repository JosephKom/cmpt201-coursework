#!/bin/bash

read -p"Username: " user
read -sp"Password: " pass

print() {
  echo Your name: "$user"
  echo Your password:"$pass"
}

print
