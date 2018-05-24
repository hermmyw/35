#!/usr/bin/python
import random, sys
from optparse import OptionParser
import string

class perm:
  def __init__(self, filename):
    if type(filename) is str:
      if filename == "-":
        self.lines = sys.stdin.readlines()
      else:
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()
    else:
      self.lines = filename
  def choosePerm(self):
    random.shuffle(self.lines)
    return self.lines
  def chooseRand(self):
    if len(self.lines) != 0:
      return random.choice(self.lines)
    return None

def main():
  version_msg = "%prog 1.0"
  usage_msg = """%prog [OPTION]... FILE

Write a random permutation of the input lines to standard output."""

  
  parser = OptionParser(version = version_msg, usage = usage_msg)
  parser.add_option("-e", "--echo", action = "store_true", dest = "echo",
                    default = False,
                    help = "treat each ARG as an input file")
  parser.add_option("-n", "--head-count", action = "store", dest = "count",
                    help = "output at most COUNT lines")
  parser.add_option("-r", "--repeat", action = "store_true", dest = "repeat",
                    default = False,
                    help = "output lines can be repeated")
  options, args = parser.parse_args(sys.argv[1:])

  count = 0
  limit = True
  if options.count ==  None:
    limit = False
  else:
    count = int(options.count)
  echo = bool(options.echo)
  repeat = bool(options.repeat)

  if limit and count < 0:
    parser.error("negative count: {0}".format(count))
    
  if echo:
    input_file = [None] * len(args)
    for index in range(len(args)):
      input_file[index] = args[index] + "\n"
  elif len(args) == 1:
    input_file = args[0]
  elif len(args) > 1:
    parser.error("wrong number of operands")
  else:
    input_file = sys.stdin.readlines()

  try:
    generator = perm(input_file)
    output = []
    if repeat:
      if generator.chooseRand() == None:
        parser.error("no lines to repeat")
    else:
      output = generator.choosePerm()
      if not limit or len(output) < count:
        count = len(output)
      for index in range(count):
        sys.stdout.write(output[index])        
  except IOError as e:
    parser.error("I/O error({0}): {1}".format(e.errno, e.strerror))


if __name__ == "__main__":
  main()
