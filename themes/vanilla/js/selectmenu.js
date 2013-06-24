(function($) {

    Drupal.behaviors.vanillaSelectmenu = {
        attach: function(cx, s) {
            $('select').selectmenu();
        }
    }

})(jQuery);
