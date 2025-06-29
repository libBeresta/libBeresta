(:файл "unicode_glyph"
 :функции
       ((:название "UnicodeToGlyphName"
	 :группа "text"
	 :ru "Для символа, заданного кодом фукнция возвращает строку с названием глифа Unicode.
  Если коду не сопоставлен глиф Unicode (в библиотеке), возвращается значение \\c .notdef"
	 :en "For given symbol code return Unicode glyph name.
  If no glyph name found (in library) value \\c .notdef is returned."
	 :параметры ((:тип "UNICODE"
		      :имя "unicode"
		      :ru "Код символа, для которого надо получить название глифа Unicode"
		      :en "Unicode symbol code to get Unicode glyph name"))
	 :результат (:тип "CSTR"
		     :ru "Название глифа Unicode"
		     :en "Unicode glyph name"))

	(:название "GlyphNameToUnicode"
	 :группа "text"
	 :ru "Для названия глифа Unicode возвращает код символа. Если название глифа не найдено или некорректно, возвращается \\c 0x0000."
	 :en "For given Unicode glyph name return symbol code. If glyph name is not found or not valid, return \\c 0x0000."
	 :параметры ((:тип "CSTR"
		      :имя "glyph_name"
		      :ru "Название глифа Unicode"
		      :en "Unicode glyph name"))
	 :результат (:тип "UNICODE"
		     :ru "Код символа, для заданного названия глифа Unicode."
		     :en "Unicode symbol code for given Unicode glyph name."))))

