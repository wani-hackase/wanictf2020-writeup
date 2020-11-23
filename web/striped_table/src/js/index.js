let old_alert = alert;

alert = (s) => {
    let text;
    old_alert(s);
    if (s === 19640503) {
        let tds = Array.from(document.querySelectorAll("tbody tr:nth-child(even) td:nth-child(3)"))
        if (tds.some(td => td.innerHTML.includes("<script") && td.innerHTML.includes("19640503"))) {
            text = "おめでとうございます！ FLAG{simple_cross_site_scripting}"
        } else {
            text = "コンソールで実行してもフラグは教えられません！"
        }
        old_alert(text)
        console.log(text)
    }
}