import sys
import subprocess

main_app = subprocess.Popen(sys.argv[1:])
raise SystemExit(main_app.wait())