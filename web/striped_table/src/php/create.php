<?php
session_start();
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  if (!empty($_POST["title"]) && !empty($_POST["memo"])) {
    $memo = $_POST;
    $memo["id"] = uniqid();
    if (isset($_SESSION["memos"])) {
      $memos = $_SESSION["memos"];
    } else {
      $memos = [];
    }
    array_push($memos, $memo);
    $_SESSION["memos"] = $memos;
    header('Location: /', true, 301);
    exit;
  } else {
    $message = "タイトルとメモは必須です。";
  }
}
?>
<?php include( $_SERVER['DOCUMENT_ROOT'] . '/includes/meta-header.php'); ?>
  <form method="post">
    <div class="form-group">
      <label for="title">タイトル</label>
      <input type="text" class="form-control" id="title" name="title" placeholder="タイトル" required>
    </div>
    <div class="form-group">
      <label for="memo">メモ</label>
      <textarea class="form-control" id="memo" name="memo" rows="3" required></textarea>
    </div>
    <button type="submit" class="btn btn-primary">送信</button>
  </form>
<?php include( $_SERVER['DOCUMENT_ROOT'] . '/includes/footer.php'); ?>