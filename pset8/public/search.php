<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    $query = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name) AGAINST (? IN BOOLEAN MODE)", $_GET["geo"] . "%");
    
    $i = 0;
    foreach($query as $q)
    {
        foreach($q as $key => $value )
        {
            $places[$i][$key] = $value;
        }
        $i++;
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>