import requests

def check_web_sql2(host):

    flag = "FLAG{5ql_ch4r_cf_ca87b27723}"
    flag_url = host + "/index.php?year=0"

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
