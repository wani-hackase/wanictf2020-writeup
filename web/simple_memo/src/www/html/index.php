<!DOCTYPE html>
<html lang="ja">
<head>
<title>The シンプル メモ張</title>
</head>

<body>
<?php
  require "reader.php";
  $file = htmlspecialchars($_GET["file"]);
  if ($file != null) {
    $content = reader($file);
    $file_title =   $file = str_replace('../', '', $file);    //preg_split("/\./", $file)[0];
    echo "<div class=\"box\"><span class=\"box-title\">{$file_title}</span>{$content}</div>";
  } else {
    echo "<h1>The シンプル メモ帳</h1>";
  }

  $memo_dir = "./memos/";
  if( is_dir( $memo_dir ) && $handle = opendir( $memo_dir ) ) {
    $memo_number = 0;
    echo "<table>";
    echo "<tr>";
    echo "<th>番号</th>";
    echo "<td>タイトル</td>";
    echo "<td>最終更新日時</td>";
    echo "</tr>";
    while( ($file = readdir($handle)) !== false ) {
	  if( filetype( $path = $memo_dir . $file ) == "file" ) {
        $memo_number = ++$memo_number;
        $file_title = preg_split("/\./", $file)[0];
        $file_last_updated = date("Y-m-d H:i:s", filemtime($path));
        echo "<tr>";
        echo "<th>{$memo_number}</th>";
        echo "<td><a href=\"./index.php?file={$file}\">{$file_title}</a></td>";
        echo "<td>{$file_last_updated}</td>";
        echo "</tr>";
	  }
    }
    echo "</table>";
  }

?>
</body>
</html>

<style>
h1 {
  padding: 0.5em;
  margin: 0.5em auto;
  width: 80%;
  color: #494949;
  background: #fffaf4;
  border-left: solid 5px #ffaf58;
}

h2 {
  position:relative;
  margin: auto;
  width: 50%
}

.box {
 position:relative;
 padding: 35px 20px 20px;
 margin: 2.5em auto;
 width: 80%;
 color: #555555;
 background-color: #f8f5e3;
 box-shadow: 0 2px 5px #999;
}
.box-title {
 position: absolute;
 top: -15px;
 left: 30px;
 padding: 4px 20px;
 color: #555555;
 font-weight: bold;
 background-color: rgba(255,255,255,.1);
 border-left: 2px dotted rgba(0,0,0,.1);
 border-right: 2px dotted rgba(0,0,0,.1);
 box-shadow: 0 0 5px rgba(0,0,0,0.2); 
 transform: rotate(-3deg);
}

table{
  position:relative;
  padding: 35px 20px 15px;
  margin: 2.5em auto;
  border-collapse: collapse;
  border-spacing: 0;
  width: 50%;
}
table tr{
  border-bottom: solid 1px #eee;
}
table tr:hover{
  background-color: #d4f0fd;
}
table th,table td{
  text-align: center;
  width: 25%;
  padding: 15px 0;
}
</style>