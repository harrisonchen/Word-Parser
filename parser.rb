## U.S. Constitution Parser ##
# A basic program that parses the U.S. Constitution
# - Retrieves line count, word count, byte count, article, sections, and more!

if File.exist?(ARGV[0])
	
	file = File.open(ARGV[0], "r")
	word_count = 0
	line_count = 0
	byte_count = 0
	proper_word_count = 0; # word count excluding words from ignore list
	proper_byte_count = 0; # byte count excluding bytes of excluded words
	article_count = 0;
	section_count = 0;

	sections_per_article = {};
	current_article = ""

	ignore_list = ["I", "We", "You", "They", "a", "and",
					"the", "that", "of", "for", "with"]

	file.each_line do |line|

		line_count += 1

		word_count += line.split.size
		byte_count += line.bytesize

		proper_line = line.split.delete_if{|word| ignore_list.include?(word)}.join(' ')

		proper_word_count += proper_line.split.size
		proper_byte_count += proper_line.bytesize

		if line.match(/^Article \d+[.]\Z/)
			article_count += 1
			current_article = line.scan(/^Article \d+/)
			if sections_per_article[current_article] == nil
				sections_per_article[current_article] = 0
			end
		end

		if line.match(/^Section \d+\Z/)
			section_count += 1
			sections_per_article[current_article] += 1
		end

	end

	file.close

	puts "all: #{line_count} #{word_count} #{byte_count} #{ARGV[0]}"
	puts "proper: #{line_count} #{proper_word_count} #{proper_byte_count}"
	puts "Total Articles: #{article_count}"
	puts "Total Sections: #{section_count}"
	puts "Total Sections per Article: "
	
	sections_per_article.to_a.reverse.each do |article|
		puts "    #{article[0]}: #{article[1]}"
	end
		
else

	puts "File does not exist"
end


