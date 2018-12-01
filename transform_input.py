from collections import defaultdict
import sys

def parse_args(typ):
  args = sys.argv[1:]
  if (typ == "b"):
    args = args[1:]

  if len(args) > 0:
    filein = args[0]
  else:
    filein = input("Enter filename to transform: ")
  if len(args) > 1:
    fileout = args[1]
  else: 
    fileout = "new_" + filein

  return filein, fileout

def get_max_dim(filein, typ=""):
  # determine max dimension
  midx = 0

  with open(filein, "r") as f:
    for line in f:
      if typ == "b":
        midx = max(midx, max([int(item) for item in line.strip().split()]))
      else:
        midx = max(midx, max([int(item.split(":")[0]) for item in line.strip().split()]))
  return midx

def transform(filein, fileout):
  midx = get_max_dim(filein)
  # print("max dim = ", midx)
  with open(fileout, "w") as fout:
    with open(filein, "r") as f:
      for line in f:
        dense_v = defaultdict(int)
        for pair in line.strip().split():
          idx, val = pair.split(":")
          dense_v[int(idx)] = float(val)

        outline = " ".join([str(dense_v[i]) for i in range(midx)])
        fout.write(outline + "\n")

def transform_binary(filein, fileout):
  midx = get_max_dim(filein, "b")
  with open(fileout, "w") as fout:
    with open(filein, "r") as f:
      for line in f:
        dense_v = defaultdict(int)
        for idx in line.strip().split():
          idx = int(idx)
          dense_v[idx] = 1

        outline = " ".join([str(dense_v[i]) for i in range(midx)])
        fout.write(outline + "\n")

def main():
  if len(sys.argv) > 1:
    typ = sys.argv[1]

  filein, fileout = parse_args(typ)

  if typ == "b":
    transform_binary(filein, fileout)
  else:
    transform(filein, fileout)

main() 
