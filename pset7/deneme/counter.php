<?php
    session_start();
    
    if(isset($_SESSION["counter"]))
    {
        $counter = $_SESSION["counter"];
    }
    else
    {
        $counter = 0;
    }
    
    $_SESSION["counter"] = $counter + 1;      
    
?> 


<!DOCTYPE <!DOCTYPE html>
<html>
    <head>
        <title>counter</title>
    </head>
    <body>
        You have visited this site <?=$counter?> times. 
    </body>
</html>