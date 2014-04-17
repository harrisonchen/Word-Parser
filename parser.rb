if File.exist?(ARGV[0])
	
	file = File.open(ARGV[0], "r")
	word_count = 0
	newline_count = 0
	byte_count = 0

	file.each_line do |line|

		newline_count += 1
		word_count += line.split.size
		byte_count += line.bytesize
	end

	file.close

	puts " #{newline_count} #{word_count} #{byte_count} #{ARGV[0]}"
else

	puts "File does not exist"
end


