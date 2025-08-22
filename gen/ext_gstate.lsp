(:файл "ext_gstate"
 :определения
      ((:имя "ExtGState"
        :оригинал "Dict"))
        
 :функции ((:название "ExtGState_SetAlphaStroke"
 :ошибки ()
 :команда "CA"
 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
 :параметры ((:тип "ExtGState"
              :имя "ext_gstate"
              :ru ":param_ext_gstate"
              :en ":param_ext_gstate")
             (:тип "REAL"
              :имя "value"
              :ru "Значение прозрачности штриха."
              :en "Alpha stroke value.")))

(:название "ExtGState_SetAlphaFill"
 :ошибки ()
 :команда "ca"
 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
 :параметры ((:тип "ExtGState"
              :имя "ext_gstate"
              :ru ":param_ext_gstate"
              :en ":param_ext_gstate")
             (:тип "REAL"
              :имя "value"
              :ru "Значение прозрачности заливки."
              :en "Alpha fill value.")))

(:название "ExtGState_SetBlendMode"
 :ошибки ()
 :команда "BM"
 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
 :параметры ((:тип "ExtGState"
              :имя "ext_gstate"
              :ru ":param_ext_gstate"
              :en ":param_ext_gstate")
             (:тип "BlendMode"
              :имя "mode"
              :ru ""
              :en "")))))
