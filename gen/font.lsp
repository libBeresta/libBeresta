(:file "font"
 :definitions
      ((:name "Font"
        :original "Dict"))

 :functions (
       (:caption "Font_Descent"
        :group "font"
        :errors ()
        :result (:type "REAL"
                    :ru ""
                    :en "")
        :ru ""
        :en ""
        :params (
        (:type "Font"
                     :name "font"
                     :ru ":param_font"
                     :en ":param_font")
        (:type "REAL"
                     :name "font_size"
                     :ru ""
                     :en "")
                     ))

       (:caption "Font_TextWidth2"
        :group "font"
        :errors ()
        :result (:type "REAL"
                    :ru ""
                    :en "")
        :ru ""
        :en ""
        :params (
        (:type "Font"
                     :name "font"
                     :ru ":param_font"
                     :en ":param_font")
        (:type "REAL"
                     :name "font_size"
                     :ru ""
                     :en "")
        (:type "REAL"
                     :name "word_space"
                     :ru ""
                     :en "")
        (:type "REAL"
                     :name "char_space"
                     :ru ""
                     :en "")
        (:type "CSTR"
                     :name "text"
                     :ru ""
                     :en "")
                     ))))
