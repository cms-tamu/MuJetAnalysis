<html>
<head>
<title><?php echo getcwd(); ?></title>
<style type='text/css'>
body {
    font-family: "Corbel", sans-serif;
    font-size: 9pt;
    line-height: 10.5pt;
}
ul.subdirs {
    padding: 0pt;
}
li.subdirs {
    display: inline;
    list-style-type: none;
    padding-right: 20px;
}
div.pic h3 { 
    font-size: 11pt;
    margin: 0.5em 1em 0.2em 1em;
}
div.pic p {
    font-size: 11pt;
    margin: 0.2em 1em 0.1em 1em;
}
div.pic {
    display: block;
    float: left;
    background-color: white;
    border: 1px solid #ccc;
    padding: 2px;
    text-align: center;
    margin: 2px 10px 10px 2px;
     -moz-box-shadow: 7px 5px 5px rgb(80,80,80);    /* Firefox 3.5 */
     -webkit-box-shadow: 7px 5px 5px rgb(80,80,80); /* Chrome, Safari */
     box-shadow: 7px 5px 5px rgb(80,80,80);         /* New browsers */  
}
a { text-decoration: none; color: rgb(0,0,80); }
a:hover { text-decoration: underline; color: rgb(255,80,80); }

</style>
</head>
<body>
<h1><CENTER><?php echo basename(getcwd()); ?></CENTER></h1>
<h2><a name="plots">Plots</a></h2>
<p><form>Filter: <input type="text" name="match" size="30" value="<?php if (isset($_GET['match'])) print htmlspecialchars($_GET['match']);  ?>" /><input type="Submit" value="Go" /></form></p>
<div>
<?php
$remainder = array();
if ($_GET['noplots']) {
  print "Plots will not be displayed.\n";
} else {
  $other_exts = array('.pdf', '.cxx', '.eps');
  foreach (glob("*") as $filename) {
    if (!preg_match('/.*\.png$/', $filename) && !preg_match('/.*\.gif.*$/', $filename)) {
      if (!preg_match('/.*\.php.*$/', $filename)) {
	array_push($remainder, $filename);
      }
      continue;
    }
    if (isset($_GET['match']) && !fnmatch('*'.$_GET['match'].'*', $filename)) continue;
    print "<div class='pic'>\n";
    print "<h3><a href=\"$filename\">$filename</a></h3>";
    print "<a href=\"$filename\"><img src=\"$filename\" style=\"border: none; width: 280px; \"></a>";
    $others = array();
    foreach ($other_exts as $ex) {
        if (file_exists(str_replace('.png', $ex, $filename))) {
            array_push($others, "<a class=\"file\" href=\"".str_replace('.png', $ex, $filename)."\">[" . $ex . "]</a>");
        }
    }
    if ($others) print "<p>".implode(', ',$others)."</p>";
    print "</div>";
  }
 }
?>
</div>
<div style="display: block; clear:both;">
  <h2><a name="files">&nbsp;<P>Files</a></h2>
<ul>
<?
foreach ($remainder as $filename) {
  print "<li><a href=\"$filename\">$filename</a></li>";
}
?>
</ul>
</div>
</body>
</html>
