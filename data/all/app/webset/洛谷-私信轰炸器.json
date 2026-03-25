async function sendMessage(uid,content){
    await fetch("https://www.luogu.com.cn/api/chat/new", {
        headers: [
            ["content-type", "application/json"],
            ["referer", "https://www.luogu.com.cn/"],
            ["x-csrf-token", document.querySelector("meta[name=csrf-token]").content],
        ],
        body: JSON.stringify({
            user: uid,
            content: content,
        }),
        method: "POST",
    });
}
(function() {
	let words = ["发送的内容"];
    let qwq = words[Math.floor(Math.random()*words.length)];
    var num;
    for(num=0;num<21;++num)sendMessage(uid,qwq);
})();
