#!/usr/bin/python                                                                        
import random, sys
from optparse import OptionParser
import string

class perm:
  def __init__(self, filename):
    if type(filename) is str:
      f = open(filename, 'r')
      self.lines = f.readlines()
      f.close()
    else:
      self.lines = filename
  def choosePerm(self):
    return random.choice(self.lines)
  def chooseIndex(self):
    return random.randint(0,len(self.lines)-1)

def main():
  version_msg = "%prog 1.0"
  usage_msg = """%prog [OPTION]... FILE                                                  
                                                                                         
Write a random permutation of the input lines to standard output."""


  parser = OptionParser(version = version_msg, usage = usage_msg)
  parser.add_option("-e", "--echo", action = "store_true", dest = "echo",
                    default = False,
                    help = "treat each ARG as an input file")
  parser.add_option("-n", "--head-count", action = "store", dest = "count",
                    default = 100,
                    help = "output at most COUNT lines")
  parser.add_option("-r", "--repeat", action = "store_true", dest = "repeat",
                    default = False,
                    help = "output lines can be repeated")

  options, args = parser.parse_args(sys.argv[1:])

  count = int(options.count)
  echo = bool(options.echo)
  repeat = bool(options.repeat)
  if count < 0:
    parser.error("negative count: {0}".format(count))
  if len(args) == 0:
    parser.error("wrong number of operands")


  if echo:
    input_file = [None] * len(args)
    for index in range(len(args)):
      input_file[index] = args[index]+'\n'
  else:
    input_file = args[0]


  try:
    generator = perm(input_file)
    output = []
    if repeat:
      for index in range(count):
        sys.stdout.write(generator.choosePerm())
    else:
      if count > len(generator.lines):
        count  = len(generator.lines)
      chosen = [None] * len(generator.lines)
      for c in range(len(chosen)):
        chosen[c] = 0
      for index in range(count):
        i = generator.chooseIndex()
        while chosen[i] == 1:
          i = generator.chooseIndex()
        chosen[i] = 1
        print(i)
        output.append(generator.lines[i])
    for index in range(len(output)):
      sys.stdout.write(output[index])
  except IOError as (errno, strerror):
    parser.error("I/O error({0}): {1}".format(errno, strerror))


if __name__ == "__main__":
  main()
