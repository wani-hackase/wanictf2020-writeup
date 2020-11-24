<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>SQL_Challenge_1</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/style.css">
</head>

<body>
    <div class="container">

        <header>
            <h1>年別アニメ視聴リスト</h1>
        </header>
        <div class="content">
            <section class="year">
                <h1>
                    <ul class="clearfix">
                        <li><a href="index.php?year=2011">2011</a></li>
                        <li><a href="index.php?year=2012">2012</a></li>
                        <li><a href="index.php?year=2013">2013</a></li>
                        <li><a href="index.php?year=2014">2014</a></li>
                        <li><a href="index.php?year=2015">2015</a></li>
                        <li><a href="index.php?year=2016">2016</a></li>
                    </ul>
                </h1>
            </section>

            <section class="list">
                <table border="1" class="clearfix">
                    <tr>
                        <th>title</th>
                        <th>year</th>
                    </tr>

                    <?php
                    
                    //mysqlへ接続する。
                    $mysqli = new mysqli('mysql', 'wani', 'waniwani', 'test_db');
                    if ($mysqli->connect_error) {
                        echo $mysqli->connect_error;
                        exit();
                    } else {
                        $mysqli->set_charset("utf8mb4");
                    }

                    //urlの"year="の後に入力した文字列を$yearに入れる。
                    $year = $_GET["year"];

                    //一部の文字は利用出来ません。以下の文字を使わずにFLAGを手に入れてください。
                    if (preg_match('/\s/', $year))
                        exit('危険を感知'); //スペース禁止
                    if (preg_match('/[\']/', $year))
                        exit('危険を感知'); //シングルクォート禁止
                    if (preg_match('/[\/\\\\]/', $year))
                        exit('危険を感知'); //スラッシュとバックスラッシュ禁止
                    if (preg_match('/[\|]/', $year))
                        exit('危険を感知'); //バーティカルバー禁止                    

                    //クエリを作成する。
                    $query = "SELECT * FROM anime WHERE years =$year";

                    //debug用にhtmlのコメントにクエリを表示させる。
                    echo "<!-- debug : ", htmlspecialchars($query), " -->\n";

                    //結果を表示させる。
                    if ($result = $mysqli->query($query)) {
                        while ($row = $result->fetch_assoc()) {
                            echo '<tr><th>' . $row['name'] .  '</th><th>' . $row['years'] . '</th></tr>';
                        }
                        $result->close();
                    }
                    ?>

                </table>
            </section>
        </div>
    </div>
</body>

</html>