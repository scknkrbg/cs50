<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="on" autofocus class="form-control" name="symbol" placeholder="Symbol (i.e., GOOG)" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="# of Shares" type="number"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-plus-sign"></span>
                Buy
            </button>
        </div>
    </fieldset>
</form>