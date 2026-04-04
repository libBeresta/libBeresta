(:file "unicode_glyph"
 :functions
       ((:caption "UnicodeToGlyphName"
	 :group "text"
	 :ru "Для символа, заданного кодом функция возвращает строку с названием глифа Unicode.
  Если коду не сопоставлен глиф Unicode (в библиотеке), возвращается значение \\c .notdef"
	 :en "For given symbol code return Unicode glyph name.
  If no glyph name found (in library) value \\c .notdef is returned."
	 :params ((:type "UNICODE"
		      :name "unicode"
		      :ru "Код символа, для которого надо получить название глифа Unicode"
		      :en "Unicode symbol code to get Unicode glyph name"))
	 :result (:type "CSTR"
		     :ru "Название глифа Unicode"
		     :en "Unicode glyph name"))

	(:caption "GlyphNameToUnicode"
	 :group "text"
	 :ru "Для названия глифа Unicode возвращает код символа. Если название глифа не найдено или некорректно, возвращается \\c 0x0000."
	 :en "For given Unicode glyph name return symbol code. If glyph name is not found or not valid, return \\c 0x0000."
	 :params ((:type "CSTR"
		      :name "glyph_name"
		      :ru "Название глифа Unicode"
		      :en "Unicode glyph name"))
	 :result (:type "UNICODE"
		     :ru "Код символа, для заданного названия глифа Unicode."
		     :en "Unicode symbol code for given Unicode glyph name."))))

