(function($){

    var focusDependenciesParse = function(dependencies, checked, name) {
        if (dependencies == '' || !dependencies) return;
        
        var dependency;
         
        for (i in dependencies) {
            if (dependencies[i] == name) continue;
            
            dependency = $('input[name="tools['+dependencies[i]+']"]');
            
            if (!dependency.length) continue;
            
            dependency.toggleClass('required-by-'+name, checked);
            
            if (checked) {
                dependency
                    .attr('checked', true)
                    .attr('disabled', true);
            } else {
                doubleDependencies = dependency.data('dependencies').split(',');
                
                for (j in doubleDependencies) {
                    $('input[name="tools['+doubleDependencies[j]+']"]').removeClass('required-by-'+dependencies[i]);
                }
                
                if (!!dependency[0] && !dependency[0].className.match(/required-by/i)) {
                    dependency
                        .removeAttr('disabled')
                        .removeAttr('checked');
                }
            }
            
            if ($.ui.button) dependency.button('refresh');
        }
        
    }
    
    var focusDependenciesInit = function(cx, s) {
        
        $('input[data-dependencies]').change(function(){
            var self = $(this);
            var dependencies = self.data('dependencies').split(',');
            var checked  = self.is(':checked');
            var name = self.attr('name').match(/tools\[(.*?)\]/i)[1];
            
            focusDependenciesParse(dependencies, checked, name);
        });
        
        $('form').submit(function(){
            $('input:disabled').removeAttr('disabled').attr('checked', 'checked');
        });
        
    }
    
    Drupal.behaviors.focusDependencies = {
        attach: focusDependenciesInit
    }
    
})(jQuery);
