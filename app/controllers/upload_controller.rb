class UploadController < ApplicationController
  def index
  end

  def index_post
  	upload = params[:upload][:file]
  	original_filename = upload.original_filename
  	upload_filename = upload.tempfile.path
  	cmd = "./get_lines_and_words #{upload_filename}"
  	cmd_res = `#{cmd}`
  	upload.tempfile.unlink
  	output_file = "#{original_filename}.tsv"
  	send_data cmd_res, 
  		:filename => output_file, 
  		:type => "text/tsv"
  end
end
