// 対象とするノードを取得
const target = document.querySelector('.card');
 
// オブザーバインスタンスを作成
const observer = new MutationObserver(_ => {
    const text = document.querySelector('.card-text').textContent;
    if (text.includes("5000000000000000")) {
        const flag = "FLAG{you_can_edit_html_using_devtools}";
        alert(flag);
        console.log(flag);
    }
});
 
// オブザーバの設定
const config = { childList: true, characterData: true, subtree: true };
 
// 対象ノードとオブザーバの設定を渡す
observer.observe(target, config);
 