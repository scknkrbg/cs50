<?php

    // configuration
    require("../includes/config.php"); 
    
    if($_SERVER["REQUEST_METHOD"] == "GET" )
    {
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"] );
        $portfolio = CS50::query("SELECT symbol, active_quantity, bought_price FROM portfolio WHERE status=1 and user_id = ?", $_SESSION["id"]);
    }
    
    
    render("portfolio.php", ["title" => "Portfolio", "cash" => $cash[0]["cash"], "portfolios" => $portfolio]);

?>

