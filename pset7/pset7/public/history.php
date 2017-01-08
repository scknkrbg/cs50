<?php

    // configuration
    require("../includes/config.php"); 
    
    if($_SERVER["REQUEST_METHOD"] == "GET" )
    {
        $history = CS50::query("SELECT 
            p.id As portfolio_id, 
            p.symbol, 
            DATE_FORMAT( p.date_created,  '%d.%m.%Y %H:%m:%s' ) AS date_bought, 
            p.bought_quantity, p.bought_price, 
            DATE_FORMAT( h.date_sold,  '%d.%m.%Y %H:%m:%s' ) AS date_sold, 
            h.sold_quantity, 
            h.sold_price,
            h.sold_price - p.bought_price as profit_per_share,
            h.sold_quantity * (h.sold_price - p.bought_price) as profit_total
        FROM portfolio p
        LEFT JOIN history h ON h.portfolio_id = p.id
        WHERE p.user_id = ? 
        ORDER BY p.id, p.date_created ASC", $_SESSION["id"]);
    }
    
    
    render("history_display.php", ["title" => "History", "history" => $history]);

?>