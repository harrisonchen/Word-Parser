if File.exist?(ARGV[0])
	
	file = File.open(ARGV[0], "r")
	word_count = 0
	line_count = 0
	byte_count = 0
	proper_word_count = 0;
	proper_byte_count = 0;

	ignore_list = ["I", "We", "You", "They", "a", "and",
					"the", "that", "of", "for", "with"]

	file.each_line do |line|

		line_count += 1

		word_count += line.split.size
		byte_count += line.bytesize

		proper_line = line.split.delete_if{|word| ignore_list.include?(word)}.join(' ')
		proper_word_count += proper_line.split.size
		proper_byte_count += proper_line.bytesize

	end

	file.close

	puts "all: #{line_count} #{word_count} #{byte_count} #{ARGV[0]}"
	puts "proper: #{line_count} #{proper_word_count} #{proper_byte_count}"
else

	puts "File does not exist"
end


