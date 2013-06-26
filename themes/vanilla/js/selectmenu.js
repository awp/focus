(function($) {

    Drupal.behaviors.vanillaSelectmenu = {
        attach: function(cx, s) {
            if (!!$.ui.selectmenu) {
                // initialize selectmenus
                $('select:visible', cx).not('[multiple]').each(function(i, el) {
                    var parent = $(el).parent();
                    $(el).selectmenu({ style: 'popup', appendTo: parent });
                });
            }
        }
    }

})(jQuery);
