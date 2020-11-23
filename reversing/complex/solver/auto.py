import angr

proj = angr.Project("./complex")

target_addr = 0x401cb9
avoid_addr = 0x401c94

state = proj.factory.entry_state()
simgr = proj.factory.simgr(state)
simgr.explore(find=target_addr, avoid=avoid_addr)
state = simgr.found[0]
print(state.posix.dumps(0))
