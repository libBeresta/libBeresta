(:file "ext_gstate"
 :definitions
      ((:name "ExtGState"
        :original "Dict"))
        
 :functions ((:caption "ExtGState_SetAlphaStroke"
 :errors ()
 :command "CA"
 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
 :params ((:type "ExtGState"
              :name "ext_gstate"
              :ru ":param_ext_gstate"
              :en ":param_ext_gstate")
             (:type "REAL"
              :name "value"
              :ru "Значение прозрачности штриха."
              :en "Alpha stroke value.")))

(:caption "ExtGState_SetAlphaFill"
 :errors ()
 :command "ca"
 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
 :params ((:type "ExtGState"
              :name "ext_gstate"
              :ru ":param_ext_gstate"
              :en ":param_ext_gstate")
             (:type "REAL"
              :name "value"
              :ru "Значение прозрачности заливки."
              :en "Alpha fill value.")))

(:caption "ExtGState_SetBlendMode"
 :errors ()
 :command "BM"
 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
 :params ((:type "ExtGState"
              :name "ext_gstate"
              :ru ":param_ext_gstate"
              :en ":param_ext_gstate")
             (:type "BlendMode"
              :name "mode"
              :ru ""
              :en "")))))
