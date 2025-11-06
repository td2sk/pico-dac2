# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "hidapi",
# ]
# ///
import hid

VID = 0xCAFE
PID = 0xBABE


device = hid.device()
device.open(VID, PID)

ret = device.write(bytes([1, 2, 3]))
if ret == -1:
    print(f"write error: {ret}")
else:
    print(f"write: {ret}")


ret = device.read(16, 1)
if ret == -1:
    print(f"read error: {ret}")
else:
    print(f"read: {ret}")
