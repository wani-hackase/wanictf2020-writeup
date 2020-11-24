import socket


def check_mis_number(host):

    flag = b"FLAG{b1n@ry_5e@rch_1s_v3ry_f@5t}"
    host = host
    port = 60000

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(3)
        s.connect((host, port))

        def recvuntil(t):
            buf = b""
            while not buf.endswith(t):
                buf += s.recv(1)
            return buf

        num_before = 0
        num_after = 500000
        for _ in range(30):
            num = (num_before + num_after) // 2
            s.send((str(num) + "\n").encode())
            result = recvuntil(b"!")
            print(result)
            if b"correct" in result:
                result = recvuntil(b"}")
                print(result)
                if flag in result:
                    return 0
                else:
                    return 1
            if b"too big" in result:
                num_after = num
            if b"too small" in result:
                num_before = num

        return 1

    except Exception as e:
        print(e)
        return 2

    finally:
        s.close()
