(function($){

    var webTreeFormsInit = function(cx, s) {

        var widgetTypes = s.fieldWidgetTypes;

        // initialize selectmenus
        if (!!$.ui.selectmenu) {
            $('select:visible').not('[multiple]').selectmenu();

            // collapsed fieldsets need manual handling for child select objects
            $('fieldset.collapsed, fieldset.field-group-tab').each(function(i, el){
                var fs = this;
                $('legend a', fs).click(function(){
                    $('select:visible', fs).selectmenu();
                });

                $('.vertical-tab-button a').click(function(){
                    $('select:visible', fs).selectmenu();
                });
            });

            // hide/show weight fields need manual handling for select objects
            $('form').each(function(i, el){
                var form = this;
                $('.tabledrag-toggle-weight', this).click(function(){
                    $('select:visible', form).selectmenu();
                });
            });

            // trigger re-build of the selectmenu if there is a dependent select box
            $('select').change(function(e){
                $(this.targetSelect).selectmenu('destroy').selectmenu();
            });
        }

        // initialize checkboxes
        // if (!!$.ui.button) $('[type="checkbox"], [type="radio"]').each(function(i, el) {
            // if (!$(el).siblings('label').is('.element-invisible')) {
                // $(el).button();
                    // .bind('change state', function(e){
                        // setTimeout(function(){ // needs this delay to not beat the original change
                            // $(e.target).button('refresh');
                        // }, 1);
                    // });
            // }
        // });

    }

    Drupal.behaviors.webtreeForms = {
        attach: webTreeFormsInit
    }

})(jQuery);
