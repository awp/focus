(function($) {

    Drupal.behaviors.webtreeVanillaSelectmenu = {
        attach: function(cx, s) {
            if (!!$.ui.selectmenu) {
                // initialize selectmenus
                $('select:visible', cx).not('[multiple]').each(function(i, el) {
                    var parent = $(el).parent();
                    $(el).selectmenu({ appendTo: parent });
                });
            }

            if (!!$.ui.button) {
                // initialize checkboxes
                $('[type="checkbox"]', cx).each(function(i, el){
                    $(el).button();
                });
            }
        }
    }

})(jQuery);
