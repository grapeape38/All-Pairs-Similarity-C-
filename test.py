import sys
import subprocess
import numpy as np

def run_prog(clean=False):
  if clean:
    # make
    cl = ["make", "clean"]
    with subprocess.Popen(cl, stdout=subprocess.PIPE) as mkclean:
        for line in mkclean.stdout:
          print(line.decode().strip())
    with subprocess.Popen(["make"], stdout=subprocess.PIPE) as mkall:
      for line in mkall.stdout:
        print(line.decode().strip())

  allp = ["./allpairs"] + sys.argv[1:]
  prog_out = []
  with subprocess.Popen(allp, stdout=subprocess.PIPE) as driver:
    for line in driver.stdout:
      out = line.decode().strip()
      if len(out.split()) == 3:
        i, j, w = out.split()
        try:
          w = float(w)
          i = int(i)
          j = int(j)
          if i > j:
            t = j
            j = i
            i = t
          out = "%s %s %.6f" % (i, j, w)
          prog_out.append(out)
        except:
          pass
      print(out)

  return sorted(prog_out)

def normalize(vec):
  # sum_sq = sum([vec[i] ** 2 for i in vec]) ** .5
  # vec = {i: vec[i] / sum_sq for i in vec}
  # return vec
  norm = np.linalg.norm(vec)
  if norm == 0:
    return vec
  return vec / norm

def dot(v1, v2):
  return sum([v1[i] * v2[j] for i, j in zip(v1, v2)])

def brute_force(filein, threshold):
  dense =  []
  with open(filein, "r") as f:
    for line in f:
      dense_v = []
      for idx, val in enumerate(line.strip().split()):
        dense_v.append(float(val))
      dense_v = np.array(dense_v)
      n = normalize(dense_v)
      dense.append(n) 
  
  output = []
  for i in range(len(dense)):
    for j in range(i+1, len(dense)):
      # w = dot(dense[i], dense[j])
      w = dense[i].dot(dense[j])
      if w > threshold:
        out = "%d %d %.6f" % (i, j, w)
        output.append(out)
  return sorted(output)

prog_out = None
br_out = None
def main(filein=None, thres=None):
  if len(sys.argv) < 2:
    print("Usage: filename -<type> (0/1/2) -t <threshold>")
    return
  
  filein = filein or sys.argv[1]

  if "-t" in sys.argv:
    thres = thres or float(sys.argv[-1])
  else:
    thres = 0.5

  prog_out = run_prog()

  br_out = brute_force(filein, thres)

  all_match = True
  if prog_out != br_out:
    for line in prog_out:
      if line not in br_out:
        print("In allpairs but not brute force:", line)
        all_match = False
    for line in br_out:
      if line not in prog_out:
        print("In brute force but not allpairs:", line)
        all_match = False
    print("Pairs in br:", len(br_out), ", pairs in allpairs:", len(prog_out))
  else:
    print("Matches brute force output")
    return True
  return False

def test_thres(filein):
  filein = sys.argv[1]

main() 

